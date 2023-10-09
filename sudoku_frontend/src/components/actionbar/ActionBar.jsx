import React from "react";

import { FaUndo, FaRedo, FaPencilAlt } from "react-icons/fa";
import { BsEraser } from "react-icons/bs";
import "./ActionBar.css";

function ActionBar(props) {
  const {
    onNumClick,
    onEraseClick,
    onUndoClick,
    onRedoClick,
    notes,
    setNotes,
    hideNotes,
  } = props;

  return (
    <div className="action-bar-container">
      <div className="action-bar-row">
        <div className="action-bar-item" onClick={() => onUndoClick()}>
          <FaUndo className="action-icon" />
          <p className="action-icon-text">Undo</p>
        </div>
        <div className="action-bar-item" onClick={() => onRedoClick()}>
          <FaRedo className="action-icon" />
          <p className="action-icon-text">Redo</p>
        </div>
        <div className="action-bar-item" onClick={() => onEraseClick()}>
          <BsEraser className="action-icon" />
          <p className="action-icon-text">Erase</p>
        </div>
        {hideNotes !== true && (
          <div
            className={
              "action-bar-item" + (notes ? " action-bar-item-selected" : "")
            }
            onClick={() => setNotes(!notes)}
          >
            <FaPencilAlt className="action-icon" />
            <p className="action-icon-text">Notes</p>
          </div>
        )}
      </div>
      <div className="action-bar-row">
        {Array.from({ length: 9 }, (_, num) => num + 1).map((i) => {
          return (
            <h6 key={i} onClick={() => onNumClick(i)}>
              {i}
            </h6>
          );
        })}
      </div>
    </div>
  );
}

export default ActionBar;
