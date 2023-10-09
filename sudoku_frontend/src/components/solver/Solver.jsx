import React, { useRef, useState } from "react";
import Board from "../board/Board";
import Button from "../ui/Button";
import { boardToVec, createBoard } from "../../util";
import "./Solver.css";
import ActionBar from "../actionbar/ActionBar";

function Solver() {
  const [board, setBoard] = useState(
    createBoard(Array.from({ length: 9 }, () => new Array(9).fill(0)))
  );
  const [loading, setLoading] = useState(false);
  const boardRef = useRef();

  const solveBoard = async () => {
    setLoading(true); // Set loading to true before starting the request

    try {
      const response = await fetch("http://localhost:8080/sudoku/solve", {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({ puzzle: boardToVec(board) }),
      });
      const data = await response.json();
      setBoard(createBoard(data));
    } catch (error) {
      console.error("Error:", error);
    } finally {
      setLoading(false); // Set loading to false after the request completes (either success or error)
    }
  };

  const resetBoardHandler = () => {
    setBoard(
      createBoard(Array.from({ length: 9 }, () => new Array(9).fill(0)))
    );
  };

  return (
    <>
      <div className="container">
        <Board ref={boardRef} board={board} setBoard={setBoard} />
        <ActionBar
          onNumClick={(num) => boardRef.current.setSelectedCellValue(num)}
          onEraseClick={() => boardRef.current.clearSelectedCell()}
          onUndoClick={() => boardRef.current.undo()}
          onRedoClick={() => boardRef.current.redo()}
          hideNotes={true}
        />
        <div className="button-container">
          <Button onClick={solveBoard}>Solve</Button>
          <Button onClick={resetBoardHandler}>Reset</Button>
        </div>
      </div>

      {loading && (
        <div className="overlay">
          Loading... {/* Replace with your loading icon/component */}
        </div>
      )}
    </>
  );
}

export default Solver;
