import React, { useEffect, useState } from "react";
import Cell from "../cell/Cell";
import './Board.css';

function Board(props) {
    const { board, setBoard, selectedCell, setSelected } = props;

    const handleCellClick = (row, col) => {
        setSelected({ row, col });
    };

    const sameSquare = (row, col, selRow, selCol) => {
        return ((Math.floor(row/ 3)) * 3) + Math.floor(col / 3) === ((Math.floor(selRow / 3)) * 3) + Math.floor(selCol / 3);
    }


    return (
        <div className="board" tabIndex="0">
            {board.map((row, rowIndex) => (
                <div className="row" key={rowIndex}>
                {row.map((cellValue, colIndex) => (
                    <Cell
                        key={`${rowIndex}-${colIndex}`}
                        value={cellValue}
                        isSelected={selectedCell && selectedCell.row === rowIndex && selectedCell.col === colIndex}
                        isPeer={selectedCell && (selectedCell.row === rowIndex || selectedCell.col === colIndex || sameSquare(rowIndex, colIndex, selectedCell.row, selectedCell.col))}
                        sameValue={selectedCell && board[selectedCell.row][selectedCell.col] === cellValue && cellValue !== 0}
                        onClick={() => handleCellClick(rowIndex, colIndex)}
                        setBoard={setBoard}
                        row={rowIndex}
                        col={colIndex}
                    />
                ))}
                </div>
            ))}
            </div>
    );
}

export default Board;