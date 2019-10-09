open DataEditorType;

let _createState = () => {renderData: RenderEditor.createData()};

let stateData = {state: _createState()};

let getStateData = () => stateData;

let getState = () => getStateData().state;

let setState = state => {
  getStateData().state = state;

  state;
};