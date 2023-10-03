import React, { useEffect, useState } from "react";
import Cell from "../cell/Cell";
import "./Board.css";

function Board(props) {
  const { board, setBoard, selectedCell, setSelected } = props;

  const handleCellClick = (row, col) => {
    setSelected({ row, col });
  };

  const sameSquare = (row, col, selRow, selCol) => {
    return (
      Math.floor(row / 3) * 3 + Math.floor(col / 3) ===
      Math.floor(selRow / 3) * 3 + Math.floor(selCol / 3)
    );
  };

  return (
    <div className="board">
      {board.map((row, rowIndex) =>
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
}

export default Board;
