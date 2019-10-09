let renderSelector = (uiState: AppStore.appState) => uiState.renderState;

module Method = {
  let _createCameraData = canvas => {
    let vMatrix =
      MatrixEngine.setLookAt(
        (0., 0.0, 5.),
        (0., 0., (-100.)),
        (0., 1., 0.),
      );

    let pMatrix =
      MatrixEngine.createIdentityMatrix4()
      |> MatrixEngine.buildPerspective((
           30.,
           (canvas##width |> Js.Int.toFloat)
           /. (canvas##height |> Js.Int.toFloat),
           1.,
           100.,
         ));

    (vMatrix, pMatrix);
  };

  let initEngine = () => {
    let state = DataEngine.createState() |> ViewEngine.setCanvasById("webgl");

    let canvas = ViewEngine.unsafeGetCanvas(state);

    state
    |> DeviceManagerEngine.setClearColor((0., 0., 0., 1.))
    |> ShaderEngine.addGLSL("shader1", (GLSL.vs1, GLSL.fs1))
    |> ShaderEngine.addGLSL("shader2", (GLSL.vs2, GLSL.fs2))
    |> GameObjectEngine.addGameObjectData(
         MatrixEngine.createIdentityMatrix4()
         |> MatrixEngine.setTranslation((0.75, 0., 0.)),
         GameObjectEngine.createTriangleGeometryData(),
         ("shader1", (1., 0., 0.)),
       )
    |> GameObjectEngine.addGameObjectData(
         MatrixEngine.createIdentityMatrix4()
         |> MatrixEngine.setTranslation((0., 0., 0.5)),
         GameObjectEngine.createTriangleGeometryData(),
         ("shader2", (0., 1., 0.)),
       )
    |> GameObjectEngine.addGameObjectData(
         MatrixEngine.createIdentityMatrix4()
         |> MatrixEngine.setTranslation(((-0.5), 0., (-2.))),
         GameObjectEngine.createTriangleGeometryData(),
         ("shader1", (0., 0., 1.)),
       )
    |> CameraEngine.setCameraData(_createCameraData(canvas))
    |> DirectorEngine.initAll(
         {
           "alpha": true,
           "depth": true,
           "stencil": false,
           "antialias": true,
           "premultipliedAlpha": true,
           "preserveDrawingBuffer": false,
         }: TinyWonderEngine.GlType.contextConfigJsObj,
       )
    |> DataEngine.setState
    |> ignore;
  };
};

[@react.component]
let make = () => {
  let dispatch = AppStore.useDispatch();
  let uiState = AppStore.useSelector(renderSelector);

  React.useEffect1(
    () => {
      Method.initEngine();

      None;
    },
    [||],
  );

  <article>
    <canvas key="canvas" id="webgl" width="400" height="400">
      {ReasonReact.string({|Please use a browser that supports "canvas"|})}
    </canvas>
    {
      uiState.isStart ?
        <button
          onClick={_ => dispatch(AppStore.RenderAction(RenderStore.Stop))}>
          {ReasonReact.string("Stop")}
        </button> :
        <button
          onClick={_ => dispatch(AppStore.RenderAction(RenderStore.Start))}>
          {ReasonReact.string("Start")}
        </button>
    }
  </article>;
};