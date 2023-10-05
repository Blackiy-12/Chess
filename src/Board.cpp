#include "Board.h"

#include "Render/RenderBuffer.h"
#include "FigureCreator.h"

#include <atomic>
#include <future>

Chess::Board::Board() 
: White(TeamColor::WHITE), Black(TeamColor::BLACK), BoardRepresantation()
{
    this->White.setupFiguresForStart(this);
    this->Black.setupFiguresForStart(this);

    this->updateBoardRepresantation();
    this->updateFigures();
}

Chess::Board::~Board()
{
}

bool Chess::Board::needToSwapPawn()
{
    return this->LockSwap;
}

void Chess::Board::pressPosition(BoardPosition Position)
{
    if (this->SelectedFigure == nullptr)
    {
        this->selectFigure(Position);

        if (this->SelectedFigure != nullptr)
            this->updatePosiblePosition();
    }
    else
    {
        for (auto& Cur : this->SelectedFigure->getPosibleNewPosition())
        {
            if (Cur == Position)
            {
                this->moveOrAtact(Position, this->SelectedFigure->getColor());
                this->swapTeam();
                this->updateBoardRepresantation();
                this->updateFigures();
                this->SelectedFigure = nullptr;
                this->updatePosiblePosition();
                return;
            }
        }

        auto TMP = this->SelectedFigure;

        this->selectFigure(Position);

        if (this->SelectedFigure != TMP)
            this->updatePosiblePosition();
        else
        {
            this->SelectedFigure = nullptr;
            this->updatePosiblePosition();
        }
    }

}

void Chess::Board::pressSwapPosition(FigureType NewFigure)
{
    if (NewFigure != FigureType::NONE)
    {
        if (this->PawnToSwap->Color == TeamColor::BLACK)
        {
            this->Black.Figures.push_back(FigureCreator::createFigure(PawnToSwap->Position, NewFigure, PawnToSwap->Color, this));
        }
        else
        {
            this->White.Figures.push_back(FigureCreator::createFigure(PawnToSwap->Position, NewFigure, PawnToSwap->Color, this));
        }

        this->LockSwap = false;

        RenderBuffer::getRenderBuffer()->RenderInfoMutex.lock();

        RenderBuffer::getRenderBuffer()->stopDrawSpawnPawn();

        RenderBuffer::getRenderBuffer()->RenderInfoMutex.unlock();

        this->updateBoardRepresantation();
        this->updateFigures();
    }   
}

void Chess::Board::unselectFigure()
{
    this->SelectedFigure = nullptr;
    this->updatePosiblePosition();
}

Chess::ByteBoard Chess::Board::getBoardRepresantation()
{
    return this->BoardRepresantation;
}

void Chess::Board::swapPawn(BoardPosition Position, TeamColor Color, BoardPosition NewPosition)
{
    if (Color == TeamColor::BLACK)
    {
        for (auto& Target : this->Black.Figures)
        {
            if (Target->getPosition() == Position)
            {
                this->Black.Figures.remove(Target);
                break;
            }
        }
    }
    else
    {
        for (auto& Target : this->White.Figures)
        {
            if (Target->getPosition() == Position)
            {
                this->White.Figures.remove(Target);
                break;
            }
        }
    }

    this->PawnToSwap = new SwapPawn{ NewPosition, Color };
    this->LockSwap = true;

    RenderBuffer::getRenderBuffer()->RenderInfoMutex.lock();

    RenderBuffer::getRenderBuffer()->drawSpawnPawn(Color);

    RenderBuffer::getRenderBuffer()->RenderInfoMutex.unlock();
}

void Chess::Board::moveRookForCasttleing(BoardPosition RookPosition, BoardPosition NewPosition)
{

    for (auto& Target : this->Black.Figures)
    {
        if (Target->getPosition() == RookPosition)
        {
            Target->setNewPosition(NewPosition);
        }
    }

    for (auto& Target : this->White.Figures)
    {
        if (Target->getPosition() == RookPosition)
        {
            Target->setNewPosition(NewPosition);
        }
    }
}

void Chess::Board::selectFigure(BoardPosition Position)
{
    if (this->CurrentTurn == TeamColor::WHITE)
    {
        if (White.TeamKing->getPosition() == Position)
        {
            this->SelectedFigure = White.TeamKing.get();
            return;
        }

        for (auto& Figure : White.Figures)
        {
            if (Figure->getPosition() == Position)
            {
                this->SelectedFigure = Figure.get();
                return;
            }
        }
    }
    else
    {
        if (Black.TeamKing->getPosition() == Position)
        {
            this->SelectedFigure = Black.TeamKing.get();
            return;
        }

        for (auto& Figure : Black.Figures)
        {
            if (Figure->getPosition() == Position)
            {
                this->SelectedFigure = Figure.get();
                return;
            }
        }
    }
}

void Chess::Board::updatePosiblePosition()
{
    RenderBuffer::getRenderBuffer()->RenderInfoMutex.lock();
    
    if (this->SelectedFigure != nullptr)
    {
        auto NewPosiblePosition = this->SelectedFigure->getPosibleNewPosition();
        RenderBuffer::getRenderBuffer()->freePosiblePosition();

        if (NewPosiblePosition.size() != 0)
            RenderBuffer::getRenderBuffer()->setupPosiblePosition(NewPosiblePosition);

        else
            this->SelectedFigure = nullptr;
    }
    else
        RenderBuffer::getRenderBuffer()->setupPosiblePosition({});

    RenderBuffer::getRenderBuffer()->RenderInfoMutex.unlock();
}


void Chess::Board::updateBoardRepresantation()
{
    this->BoardRepresantation.free();

    this->BoardRepresantation.setFigure(Black.TeamKing->getPosition(), TeamColor::BLACK, FigureType::KING);

    this->BoardRepresantation.setFigure(White.TeamKing->getPosition(), TeamColor::WHITE, FigureType::KING);

    for (auto& CurFigure : this->Black.Figures)
    {
        this->BoardRepresantation.setFigure(CurFigure->getPosition(), TeamColor::BLACK, CurFigure->getFigureType(), CurFigure->wasLastMoveLong(), CurFigure->isMoved());
    }

    for (auto& CurFigure : this->White.Figures)
    {
        this->BoardRepresantation.setFigure(CurFigure->getPosition(), TeamColor::WHITE, CurFigure->getFigureType(), CurFigure->wasLastMoveLong(), CurFigure->isMoved());
    }

}

void Chess::Board::updateFigures()
{   
    std::atomic_bool Finished = false;

    std::atomic_int CountToUpdate = 2 + this->Black.Figures.size() + this->White.Figures.size();
    
    std::vector<std::future<void>> Futures;

    auto asyncFunc = [&](Figure* FigureToUpdate)
    {
        FigureToUpdate->updatePosiblePosition();

        CountToUpdate--;

        if (CountToUpdate == 0)
        {
            Finished = true;
            Finished.notify_one();
        }
    };

    Futures.push_back(std::async(std::launch::async, asyncFunc, dynamic_cast<Figure*>(Black.TeamKing.get())));

    Futures.push_back(std::async(std::launch::async, asyncFunc, dynamic_cast<Figure*>(White.TeamKing.get())));


    for (auto& CurFigure : this->Black.Figures)
    {
        Futures.push_back(std::async(std::launch::async, asyncFunc, CurFigure.get()));
    }

    for (auto& CurFigure : this->White.Figures)
    {
        Futures.push_back(std::async(std::launch::async, asyncFunc, CurFigure.get()));
    }

    Finished.wait(false);

    checkMate();
}

void Chess::Board::moveOrAtact(BoardPosition NewPos, TeamColor ColorOfFigure)
{
    if (this->BoardRepresantation.getColor(NewPos.x, NewPos.y) != TeamColor::NONE)
    {

        if (ColorOfFigure == TeamColor::BLACK)
        {
            for (auto& Figure : this->White.Figures)
            {
                if (Figure->getPosition() == NewPos)
                {
                    this->White.Figures.remove(Figure);
                    break;
                }
            }
        }
        else
        {
            for (auto& Figure : this->Black.Figures)
            {
                if (Figure->getPosition() == NewPos)
                {
                    this->Black.Figures.remove(Figure);
                    break;
                }
            }
        }
    }

    if (this->SelectedFigure->getFigureType() == FigureType::PAWN)
    {
        if (std::abs(NewPos.x - this->SelectedFigure->getPosition().x) > 0)
        {
            if (this->BoardRepresantation.getColor(NewPos.x, NewPos.y) == TeamColor::NONE)
            {
                BoardPosition FigToDelete = NewPos;
                
                FigToDelete.y = this->SelectedFigure->getPosition().y;

                if (ColorOfFigure == TeamColor::BLACK)
                {
                    for (auto& Figure : this->White.Figures)
                    {
                        if (Figure->getPosition() == FigToDelete)
                        {
                            this->White.Figures.remove(Figure);
                            break;
                        }
                    }
                }
                else
                {
                    for (auto& Figure : this->Black.Figures)
                    {
                        if (Figure->getPosition() == FigToDelete)
                        {
                            this->Black.Figures.remove(Figure);
                            break;
                        }
                    }
                }
            }

        }
    }

    this->SelectedFigure->setNewPosition(NewPos);

    this->updateBoardRepresantation();
    this->updateFigures();
}

void Chess::Board::swapTeam()
{
    if (this->CurrentTurn == TeamColor::BLACK)
        this->CurrentTurn = TeamColor::WHITE;
    else
        this->CurrentTurn = TeamColor::BLACK;
}

void Chess::Board::checkMate()
{
    if (CurrentTurn == TeamColor::BLACK)
    {
        if (Black.TeamKing->getPosibleNewPosition().size() != 0)
            return;

        for (auto& Figure : Black.Figures)
        {
            if (Figure->getPosibleNewPosition().size() != 0)
                return;
        }

        this->Mate = true;
    }
    else
    {
        if (White.TeamKing->getPosibleNewPosition().size() != 0)
            return;

        for (auto& Figure : White.Figures)
        {
            if (Figure->getPosibleNewPosition().size() != 0)
                return;
        }

        this->Mate = true;
    }
}
