import React, { useImperativeHandle, useState } from "react";
import useKeypress from "react-use-keypress";
import Cell from "../cell/Cell";
import "./Board.css";

const Board = React.forwardRef((props, ref) => {
  const { board, setBoard, notes } = props;
  const [selectedCell, setSelectedCell] = useState(null);

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

  useImperativeHandle(ref, () => ({
    setSelectedCellValue: setSelectedCellAsNum,
    clearSelectedCell: clearSelectedCell,
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
