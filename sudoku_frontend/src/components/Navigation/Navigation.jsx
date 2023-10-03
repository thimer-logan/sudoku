import { Link } from "react-router-dom";
import HomeIcon from "@mui/icons-material/Home";

import "./Navigation.css";

function Navigation() {
  return (
    <header className="header">
      <h1>Sudoku</h1>
      <Link className="header-button" to="/">
        <HomeIcon />
      </Link>
    </header>
  );
}

export default Navigation;
