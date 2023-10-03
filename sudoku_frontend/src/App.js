import { RouterProvider, createBrowserRouter } from "react-router-dom";
import RootLayout from "./pages/Root";

import "./App.css";
import HomePage from "./pages/Home";
import Game from "./components/game/Game";
import Generator from "./components/generator/Generator";

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
    ],
  },
]);

function App() {
  return <RouterProvider router={router} />;
}

export default App;
