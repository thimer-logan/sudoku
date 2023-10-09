export const Difficulty = Object.freeze({
  EASY: "Easy",
  MEDIUM: "Medium",
  HARD: "Hard",
  EXTREME: "Extreme",
});

export const DifficultyOptions = [
  { value: "easy", label: "Easy" },
  { value: "medium", label: "Medium" },
  { value: "hard", label: "Hard" },
  { value: "extreme", label: "Extreme" },
];

export const sameSquare = (row, col, selRow, selCol) => {
  return (
    Math.floor(row / 3) * 3 + Math.floor(col / 3) ===
    Math.floor(selRow / 3) * 3 + Math.floor(selCol / 3)
  );
};

export const createBoard = (puzzle) => {
  const newBoard = [];

  for (let i = 0; i < puzzle.length; i++) {
    const row = [];
    for (let j = 0; j < puzzle[i].length; j++) {
      row.push({
        value: puzzle[i][j],
        editable: puzzle[i][j] === 0 ? true : false,
        notes: new Set(),
        row: i,
        col: j,
        conflict: false,
      });
    }

    newBoard.push(row);
  }

  return newBoard;
};

export const boardToVec = (puzzle) => {
  const new_board = [];
  for (let i = 0; i < 9; i++) {
    const row = [];
    for (let j = 0; j < 9; j++) {
      row.push(puzzle[i][j].value);
    }

    new_board.push(row);
  }

  return new_board;
};
