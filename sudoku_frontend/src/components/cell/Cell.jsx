import React from "react";
import PropTypes from 'prop-types';
import './Cell.css';

function Cell(props) {
    const {
        value, onClick, isPeer, isSelected, sameValue, isEditable, notes, conflict, row, col
    } = props;

    return (
        <div className={"cell" + (row === 2 || row === 5 ? " cell-border-bottom" : "") + (isSelected ? " cell-selected" : (sameValue ? " cell-sameval" : (isPeer ? " cell-peer" : "")))}
             onClick={onClick}>
            {
                value !== 0 ? value : 
                (notes ?
                    Array.from({length: 9}, (_, num) => num + 1).map((i) => {
                        return (<div className="note" key={i}>
                            {notes.has(i) && i}
                        </div>)
                    }) : null)
                    
            }

        </div>
    );
};

Cell.propTypes = {
    // current number value
    value: PropTypes.number,

    // cell click handler
    onClick: PropTypes.func.isRequired,

    // if the cell is a peer of the selected cell
    isPeer: PropTypes.bool,

    // if the cell is selected by the user
    isSelected: PropTypes.bool,

    // current cell has the same value if the user selected cell
    sameValue: PropTypes.bool,

    // if this was prefilled as a part of the puzzle
    isEditable: PropTypes.bool,

    // current notes taken on the cell
    notes: PropTypes.instanceOf(Set),

    // if the current cell does not satisfy the game constraint
    conflict: PropTypes.bool,

    // row index of the cell
    row: PropTypes.number.isRequired,

    // column index of the cell
    col: PropTypes.number.isRequired,
};
  
Cell.defaultProps = {
    notes: null,
    value: null,
};

export default Cell;