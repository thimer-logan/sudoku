import React, { useEffect, useState } from "react";
import useKeypress from 'react-use-keypress';
import ActionBar from "../actionbar/ActionBar";
import Board from "../board/Board";
import './Game.css';

function Game() {
    const [board, setBoard] = useState([]);    
    const [notes, setNotes] = useState(false);
    const [selectedCell, setSelectedCell] = useState(null);

    const setSelectedCellAsNum = (num) => {
        const newBoard = [...board];

        if (selectedCell && board[selectedCell.row][selectedCell.col].value === 0 && board[selectedCell.row][selectedCell.col].editable) {
            if (notes) {
                if (board[selectedCell.row][selectedCell.col].notes.has(num)) {
                    board[selectedCell.row][selectedCell.col].notes.delete(num);
                }
                else {
                    board[selectedCell.row][selectedCell.col].notes.add(num);
                }
            }
            else {
                newBoard[selectedCell.row][selectedCell.col].value = num;
                
            }

            setBoard(newBoard);            
        }
    }

    const clearSelectedCell = () => {
        if (selectedCell && board[selectedCell.row][selectedCell.col].value !== 0 && board[selectedCell.row][selectedCell.col].editable) {
            const newBoard = [...board];
            newBoard[selectedCell.row][selectedCell.col].value = 0;
            setBoard(newBoard);
        }
    }

    const createBoard = (puzzle) => {
        const newBoard = [];

        for (let i = 0; i < puzzle.length; i++) {
            const row = [];
            for (let j = 0; j < puzzle[i].length; j++) {
                row.push({
                    value: puzzle[i][j],
                    editable: puzzle[i][j] === 0 ? true : false,
                    notes: new Set(),
                    row: i,
                    col: j
                });
            }

            newBoard.push(row);
        }

        return newBoard;
    }

    const getBoard = async () => {
        await fetch('http://127.0.0.1:8080/sudoku/board')
        .then(res => res.json())
        .then((response)=> {
            setBoard(createBoard(response));
          },
          (err)=> {
            console.log(err);
          }
        );
    } 

    useKeypress(['1', '2', '3', '4', '5', '6', '7', '8', '9'], (event) => {
        setSelectedCellAsNum(parseInt(event.key));
    });

    useEffect(() => {
        getBoard();
    }, []);

    return (
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
    );

}

export default Game;