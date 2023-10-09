import React from "react";

import "./Button.css";

function Button({ className, onClick, children }) {
  return (
    <button className={`button ${className}`} onClick={onClick}>
      {children}
    </button>
  );
}

export default Button;
