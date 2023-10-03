import { Outlet } from "react-router-dom";
import Navigation from "../components/Navigation/Navigation";

function RootLayout() {
  return (
    <div className="main-container">
      <Navigation />

      <Outlet />
    </div>
  );
}

export default RootLayout;
