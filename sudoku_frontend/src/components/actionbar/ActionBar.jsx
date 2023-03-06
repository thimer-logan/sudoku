import React from "react";

import { FaUndo, FaRedo, FaPencilAlt } from "react-icons/fa";
import { BsEraser } from "react-icons/bs";
import Container from "react-bootstrap/Container";
import Row from "react-bootstrap/Row";
import Col from "react-bootstrap/Col";
import "./ActionBar.css";

function ActionBar(props) {
    const { onNumClick } = props;
    return (
        <div className="action-bar-container">
            <div className="action-bar-row">
                <div className="action-bar-item">
                    <FaUndo className="action-icon" />
                    <p className="action-icon-text">Undo</p>
                </div>
                <div className="action-bar-item">
                    <FaRedo className="action-icon" />
                    <p className="action-icon-text">Redo</p>
                </div>
                <div className="action-bar-item">
                    <BsEraser className="action-icon" />
                    <p className="action-icon-text">Erase</p>
                </div>
                <div className="action-bar-item">
                    <FaPencilAlt className="action-icon" />
                    <p className="action-icon-text">Notes</p>
                </div>
            </div>
            <div className="action-bar-row">
                {Array.from({length: 9}, (_, num) => num + 1).map((i) => {
                    return <h6 onClick={() => onNumClick(i)}>{i}</h6>
                }) }
            </div>
        </div>
    );
}

export default ActionBar;
