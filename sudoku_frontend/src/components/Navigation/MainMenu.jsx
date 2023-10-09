import { Link } from "react-router-dom";

import "./MainMenu.css";

function MainMenu() {
  return (
    <div className="main-btn-container">
      <Link to="/game">
        <button className="main-btn">Play Game</button>
      </Link>
      <Link to="/generator">
        <button className="main-btn">Board Generator</button>
      </Link>
      <Link to="/solver">
        <button className="main-btn">Solver</button>
      </Link>
    </div>
  );
}

export default MainMenu;
