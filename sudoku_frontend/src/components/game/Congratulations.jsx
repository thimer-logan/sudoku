import { useState, useEffect } from "react";

import "./Congratulations.css";

const Congratulations = () => {
  const [animationFinished, setAnimationFinished] = useState(false);

  useEffect(() => {
    const timer = setTimeout(() => {
      setAnimationFinished(true);
    }, 2000); // same duration as the CSS animation

    return () => {
      clearTimeout(timer);
    };
  }, []);

  return (
    <div className="congrats-container">
      <h1>Congratulations !</h1>
      {animationFinished && (
        <button className="btn slide-in">Play Again!</button>
      )}
    </div>
  );
};

export default Congratulations;
