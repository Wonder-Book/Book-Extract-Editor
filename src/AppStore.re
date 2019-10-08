type counterAction =
  | Increment
  | Decrement;

let counterReduce = (state, action) =>
  switch (action) {
  | Increment => state + 1
  | Decrement => state - 1
  };

type stringAction =
  | AppendA
  | AppendB;

let stringReduce = (state, action) =>
  switch (action) {
  | AppendA => state ++ "A"
  | AppendB => state ++ "B"
  };

type appAction =
  | StringAction(stringAction)
  | CounterAction(counterAction);

type appState = {
  counter: int,
  content: string,
};

let appReducer = (state, action) =>
  switch (action) {
  | StringAction(action) => {
      ...state,
      content: stringReduce(state.content, action),
    }
  | CounterAction(action) => {
      ...state,
      counter: counterReduce(state.counter, action),
    }
  | _ => state
  };

let appStore =
  Reductive.Store.create(
    ~reducer=appReducer,
    ~preloadedState={counter: 0, content: ""},
    (),
  );

include ReductiveContext.Make({
  type state = appState;
  type action = appAction;
});