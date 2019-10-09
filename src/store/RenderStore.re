type renderState = {isStart: bool};

type renderAction =
  | Start
  | Stop;

let createState = () => {isStart: false};

module Method = {
  let start = state => {
    let rec _loop = () =>
      DomExtend.requestAnimationFrame(time => {
        DataEngine.unsafeGetState()
        |> DirectorEngine.loopBody
        |> DataEngine.setState
        |> ignore;

        _loop();
      })
      |> RenderEditor.setLoopId(_, DataEditor.getState())
      |> DataEditor.setState
      |> ignore;

    _loop();

    {...state, isStart: true};
  };

  let stop = state => {
    DomExtend.cancelAnimationFrame(
      RenderEditor.unsafeGetLoopId(DataEditor.getState()),
    );

    {...state, isStart: false};
  };
};

let renderReduce = (state, action) =>
  switch (action) {
  | Start => Method.start(state)
  | Stop => Method.stop(state)
  };