import React, { useState } from "react";

import Dropdown from "../ui/Dropdown";
import "./GameSettings.css";
import { DifficultyOptions } from "../../util";

const GameSettings = (props) => {
  const [difficulty, setDifficulty] = useState("");
  const [difficultySet, setDifficultySet] = useState(false);

  const difficultyChangeHandler = (selectedOption) => {
    setDifficulty(selectedOption.value);
    setDifficultySet(true);
  };

  const submitHandler = (event) => {
    event.preventDefault();
    props.onSubmit(difficulty);
  };

  return (
    <form onSubmit={submitHandler} className="settings-container">
      <h1>Select your difficulty</h1>
      <Dropdown
        onChange={difficultyChangeHandler}
        options={DifficultyOptions}
        placeholder="Difficulty"
      />
      {difficultySet && (
        <button className="btn" type="submit">
          Start Game
        </button>
      )}
    </form>
  );
};

export default GameSettings;
