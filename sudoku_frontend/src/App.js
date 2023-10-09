import { RouterProvider, createBrowserRouter } from "react-router-dom";
import RootLayout from "./pages/Root";

import "./App.css";
import HomePage from "./pages/Home";
import Game from "./components/game/Game";
import Generator from "./components/generator/Generator";
import Solver from "./components/solver/Solver";

const router = createBrowserRouter([
  {
    path: "/",
    element: <RootLayout />,
    children: [
      {
        index: true,
        element: <HomePage />,
      },
      {
        path: "/game",
        element: <Game />,
      },
      {
        path: "/generator",
        element: <Generator />,
      },
      {
        path: "/solver",
        element: <Solver />,
      },
    ],
  },
]);

function App() {
  return <RouterProvider router={router} />;
}

export default App;
