import React, { useEffect, useState } from "react";
import useKeypress from 'react-use-keypress';
import ActionBar from "../actionbar/ActionBar";
import Board from "../board/Board";
import './Game.css';

function Game() {
    const [board, setBoard] = useState([
        [0, 1, 0, 0, 2, 3, 6, 0, 7],
        [0, 0, 0, 0, 0, 0, 9, 0, 0],
        [6, 0, 0, 0, 0, 0, 2, 5, 0],
        [0, 0, 4, 1, 0, 2, 5, 3, 8],
        [0, 0, 2, 8, 0, 0, 4, 0, 0],
        [5, 0, 8, 0, 0, 0, 0, 6, 0],
        [8, 0, 0, 2, 0, 9, 0, 0, 0],
        [0, 0, 9, 0, 0, 0, 0, 0, 6],
        [0, 0, 0, 7, 3, 0, 0, 0, 0],
    ]);

    const [selectedCell, setSelectedCell] = useState(null);

    const setSelectedCellAsNum = (num) => {
        if (selectedCell && board[selectedCell.row][selectedCell.col] === 0) {
            const newBoard = [...board];
            newBoard[selectedCell.row][selectedCell.col] = num;
            setBoard(newBoard);
        }
    }

    useKeypress(['1', '2', '3', '4', '5', '6', '7', '8', '9'], (event) => {
        setSelectedCellAsNum(parseInt(event.key));
    });

    return (
        <div className="container">
            <Board
                board={board}
                setBoard={setBoard}
                selectedCell={selectedCell}
                setSelected={setSelectedCell}
            />
            <ActionBar onNumClick={setSelectedCellAsNum}/>
        </div>
    );

}

export default Game;