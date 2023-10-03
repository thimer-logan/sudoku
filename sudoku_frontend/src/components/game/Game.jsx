import React, { useEffect, useState } from "react";
import useKeypress from "react-use-keypress";
import ActionBar from "../actionbar/ActionBar";
import Board from "../board/Board";
import "./Game.css";
import { sameSquare, createBoard } from "../../util";
import GameSettings from "./GameSettings";
import Congratulations from "./Congratulations";

function Game() {
  const [board, setBoard] = useState([]);
  const [notes, setNotes] = useState(false);
  const [selectedCell, setSelectedCell] = useState(null);
  const [gameComplete, setGameComplete] = useState(false);
  const [boardInitialized, setBoardInitialized] = useState(false);
  const [settingsConfirmed, setSettingsConfirmed] = useState(false);
  const [difficulty, setDifficulty] = useState("");

  const setSelectedCellAsNum = (num) => {
    const newBoard = [...board];

    if (
      selectedCell &&
      board[selectedCell.row][selectedCell.col].value === 0 &&
      board[selectedCell.row][selectedCell.col].editable
    ) {
      if (notes) {
        if (board[selectedCell.row][selectedCell.col].notes.has(num)) {
          board[selectedCell.row][selectedCell.col].notes.delete(num);
        } else {
          board[selectedCell.row][selectedCell.col].notes.add(num);
        }
      } else {
        newBoard[selectedCell.row][selectedCell.col].value = num;
        checkConflict(newBoard, newBoard[selectedCell.row][selectedCell.col]);
      }

      setBoard(newBoard);
    }
  };

  const checkConflict = (brd, cell) => {
    for (let i = 0; i < brd.length; i++) {
      for (let j = 0; j < brd[i].length; j++) {
        let cell = brd[i][j];

        if (cell.value === 0) {
          continue;
        }

        // initialize the conflict field to false for each item
        cell.conflict = false;

        for (let m = 0; m < brd.length; m++) {
          for (let n = 0; n < brd[m].length; n++) {
            let item = brd[m][n];

            // check if the item is in the same row or column as the outer cell,
            // has the same value, and is not the outer cell itself
            if (
              (item.row === cell.row ||
                item.col === cell.col ||
                sameSquare(cell.row, cell.col, item.row, item.col)) &&
              item.value === cell.value &&
              !(item.row === cell.row && item.col === cell.col)
            ) {
              cell.conflict = true;
              item.conflict = true;
            }
          }
        }
      }
    }
  };

  const clearSelectedCell = () => {
    if (
      selectedCell &&
      board[selectedCell.row][selectedCell.col].value !== 0 &&
      board[selectedCell.row][selectedCell.col].editable
    ) {
      const newBoard = [...board];
      newBoard[selectedCell.row][selectedCell.col].value = 0;
      checkConflict(newBoard);
      setBoard(newBoard);
    }
  };

  useKeypress(["1", "2", "3", "4", "5", "6", "7", "8", "9"], (event) => {
    setSelectedCellAsNum(parseInt(event.key));
  });

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
  }, [settingsConfirmed]);

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
            board={board}
            setBoard={setBoard}
            selectedCell={selectedCell}
            setSelected={setSelectedCell}
          />
          <ActionBar
            onNumClick={setSelectedCellAsNum}
            onEraseClick={clearSelectedCell}
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
