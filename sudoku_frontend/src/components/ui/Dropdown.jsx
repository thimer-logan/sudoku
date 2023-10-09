import React from "react";
import Select from "react-select";
import "./Dropdown.css";

const Dropdown = (props) => {
  const handleChange = (selectedOption) => {
    props.onChange(selectedOption);
  };

  return (
    <div>
      <Select
        options={props.options}
        onChange={handleChange}
        classNamePrefix="dropdown"
        isDisabled={props.disabled}
        placeholder={props.placeholder}
      />
    </div>
  );
};

export default Dropdown;
