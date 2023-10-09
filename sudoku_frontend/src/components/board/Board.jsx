import React, { useImperativeHandle, useState } from "react";
import useKeypress from "react-use-keypress";
import Cell from "../cell/Cell";
import "./Board.css";
import _ from "lodash";

const Board = React.forwardRef((props, ref) => {
  const { board, setBoard, notes } = props;
  const [selectedCell, setSelectedCell] = useState(null);
  const [history, setHistory] = React.useState([]);
  const [future, setFuture] = React.useState([]);

  const handleCellClick = (row, col) => {
    setSelectedCell({ row, col });
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

  const sameSquare = (row, col, selRow, selCol) => {
    return (
      Math.floor(row / 3) * 3 + Math.floor(col / 3) ===
      Math.floor(selRow / 3) * 3 + Math.floor(selCol / 3)
    );
  };

  const setSelectedCellAsNum = (num) => {
    if (
      selectedCell &&
      board[selectedCell.row][selectedCell.col].value === 0 &&
      board[selectedCell.row][selectedCell.col].editable
    ) {
      setHistory([...history, _.cloneDeep(board)]);
      setFuture([]); // Clear any redo history

      const newBoard = [...board];

      if (notes) {
        if (board[selectedCell.row][selectedCell.col].notes.has(num)) {
          newBoard[selectedCell.row][selectedCell.col].notes.delete(num);
        } else {
          newBoard[selectedCell.row][selectedCell.col].notes.add(num);
        }
      } else {
        newBoard[selectedCell.row][selectedCell.col].value = num;
        checkConflict(newBoard, newBoard[selectedCell.row][selectedCell.col]);
      }

      setBoard(newBoard);
    }
  };

  const clearSelectedCell = () => {
    if (
      selectedCell &&
      board[selectedCell.row][selectedCell.col].value !== 0 &&
      board[selectedCell.row][selectedCell.col].editable
    ) {
      const newBoard = [...board];
      setHistory([...history, _.cloneDeep(board)]);
      setFuture([]); // Clear any redo history
      newBoard[selectedCell.row][selectedCell.col].value = 0;
      checkConflict(newBoard);
      setBoard(newBoard);
    }
  };

  const undo = () => {
    console.log("Undo");
    if (history.length === 0) return;
    console.log(history);
    const lastState = history[history.length - 1];
    console.log(lastState);
    setFuture([_.cloneDeep(board), ...future]);
    setBoard(lastState);
    setHistory(history.slice(0, -1));
  };

  const redo = () => {
    console.log("Redo");
    if (future.length === 0) return;

    const nextState = future[0];
    setHistory([...history, board]);
    setBoard(nextState);
    setFuture(future.slice(1));
  };

  useKeypress(["1", "2", "3", "4", "5", "6", "7", "8", "9"], (event) => {
    setSelectedCellAsNum(parseInt(event.key));
  });

  useImperativeHandle(ref, () => ({
    setSelectedCellValue: setSelectedCellAsNum,
    clearSelectedCell: clearSelectedCell,
    undo: undo,
    redo: redo,
  }));

  return (
    <div className="board">
      {board.map((row, _) =>
        row.map((cell) => (
          <Cell
            key={`${cell.row}-${cell.col}`}
            value={cell.value}
            isSelected={
              selectedCell &&
              selectedCell.row === cell.row &&
              selectedCell.col === cell.col
            }
            isPeer={
              selectedCell &&
              (selectedCell.row === cell.row ||
                selectedCell.col === cell.col ||
                sameSquare(
                  cell.row,
                  cell.col,
                  selectedCell.row,
                  selectedCell.col
                ))
            }
            sameValue={
              selectedCell &&
              board[selectedCell.row][selectedCell.col].value === cell.value &&
              cell.value !== 0
            }
            onClick={() => handleCellClick(cell.row, cell.col)}
            setBoard={setBoard}
            notes={cell.notes}
            row={cell.row}
            col={cell.col}
            conflict={cell.conflict}
          />
        ))
      )}
    </div>
  );
});

export default Board;
