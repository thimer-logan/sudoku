import React, { useEffect, useRef, useState } from "react";
import ActionBar from "../actionbar/ActionBar";
import Board from "../board/Board";
import "./Game.css";
import { createBoard } from "../../util";
import GameSettings from "./GameSettings";
import Congratulations from "./Congratulations";

function Game() {
  const [board, setBoard] = useState([]);
  const [notes, setNotes] = useState(false);
  const [gameComplete, setGameComplete] = useState(false);
  const [boardInitialized, setBoardInitialized] = useState(false);
  const [settingsConfirmed, setSettingsConfirmed] = useState(false);
  const [difficulty, setDifficulty] = useState("");

  const boardRef = useRef();

  const settingsConfirmedHandler = (difficulty) => {
    setDifficulty(difficulty);
    setSettingsConfirmed(true);
  };

  useEffect(() => {
    const generateBoard = async () => {
      const data = {
        difficulty: difficulty,
      };
      const queryParams = new URLSearchParams(data).toString();
      const uri = `http://localhost:8080/sudoku/generate?${queryParams}`;

      await fetch(uri)
        .then(
          (res) => res.json(),
          (err) => {
            setBoard(
              createBoard(Array.from({ length: 9 }, () => new Array(9).fill(0)))
            );
            setBoardInitialized(true);
          }
        )
        .then(
          (response) => {
            setBoard(createBoard(response));
            setBoardInitialized(true);
          },
          (err) => {
            console.log(err);
          }
        );
    };

    if (settingsConfirmed) {
      generateBoard();
    }
  }, [settingsConfirmed, difficulty]);

  useEffect(() => {
    const checkCompletion = () => {
      for (let i = 0; i < board.length; i++) {
        for (let j = 0; j < board[i].length; j++) {
          if (board[i][j].value === 0 || board[i][j].conflict) {
            return false;
          }
        }
      }

      return true;
    };

    if (boardInitialized && checkCompletion()) {
      setGameComplete(true);
    }
  }, [board, boardInitialized]);

  return (
    <React.Fragment>
      {!settingsConfirmed && (
        <GameSettings onSubmit={settingsConfirmedHandler} />
      )}
      {settingsConfirmed && !gameComplete && (
        <div className="container">
          <Board
            ref={boardRef}
            board={board}
            setBoard={setBoard}
            notes={notes}
          />
          <ActionBar
            onNumClick={(num) => boardRef.current.setSelectedCellValue(num)}
            onEraseClick={() => boardRef.current.clearSelectedCell()}
            onUndoClick={() => boardRef.current.undo()}
            onRedoClick={() => boardRef.current.redo()}
            notes={notes}
            setNotes={setNotes}
          />
        </div>
      )}
      {settingsConfirmed && gameComplete && <Congratulations />}
    </React.Fragment>
  );
}

export default Game;
