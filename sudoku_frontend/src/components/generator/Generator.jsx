import React, { useState, useEffect } from "react";

import FormControlLabel from "@mui/material/FormControlLabel";
import Switch from "@mui/material/Switch";
import Board from "../board/Board";
import Dropdown from "../ui/Dropdown";
import "./Generator.css";
import { DifficultyOptions, createBoard } from "../../util";

const Generator = () => {
  const [board, setBoard] = useState([]);
  const [difficulty, setDifficulty] = useState("");
  const [fullBoardChecked, setFullBoardChecked] = useState(true);

  const generateBoard = async () => {
    const data = {
      difficulty: difficulty,
    };
    console.log(difficulty);
    const queryParams = new URLSearchParams(data).toString();
    const uri = fullBoardChecked
      ? `http://localhost:8080/sudoku/generate`
      : `http://localhost:8080/sudoku/generate?${queryParams}`;

    await fetch(uri)
      .then(
        (res) => res.json(),
        (err) =>
          setBoard(
            createBoard(Array.from({ length: 9 }, () => new Array(9).fill(0)))
          )
      )
      .then(
        (response) => {
          setBoard(createBoard(response));
        },
        (err) => {
          console.log(err);
        }
      );
  };

  const difficultyChangeHandler = (selectedOption) => {
    setDifficulty(selectedOption.value);
  };

  const fullBoardChangeHandler = (event) => {
    setFullBoardChecked(event.target.checked);
  };

  useEffect(() => {
    setBoard(
      createBoard(Array.from({ length: 9 }, () => new Array(9).fill(0)))
    );
  }, []);

  return (
    <div className="generator">
      <Board board={board} setBoard={setBoard} />
      <div className="generator-options">
        <FormControlLabel
          control={
            <Switch
              checked={fullBoardChecked}
              onChange={fullBoardChangeHandler}
            />
          }
          label="Full Board"
          sx={{ color: "white" }}
        />
        {!fullBoardChecked && (
          <Dropdown
            onChange={difficultyChangeHandler}
            options={DifficultyOptions}
            disabled={fullBoardChecked}
            placeholder="Difficulty"
          />
        )}
        <button className="generator-btn" onClick={generateBoard}>
          Generate
        </button>
      </div>
    </div>
  );
};

export default Generator;
