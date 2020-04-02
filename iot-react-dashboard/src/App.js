import React from "react";
import Header from "./components/Header";
import InfoTable from "./components/InfoTable";
import IOTComponents from "./components/IOTComponents";
import { Grid, useMediaQuery } from "@material-ui/core";

function App() {
  const greatherThanSmall = useMediaQuery(theme => theme.breakpoints.up("sm"));
  const greatherThanMedium = useMediaQuery(theme => theme.breakpoints.up("md"));
  return (
    <>
      <Header />
      <Grid
        container
        spacing={1}
        style={{
          paddingTop: greatherThanSmall ? 100 : 60,
          paddingLeft: greatherThanMedium ? 30 : 0,
          paddingRight: greatherThanMedium ? 30 : 0,
          position: greatherThanMedium ? "fixed" : "initial"
        }}
      >
        <Grid item xs={12} md={7}>
          <InfoTable />
        </Grid>

        <Grid item xs={12} md={5}>
          <IOTComponents />
        </Grid>
      </Grid>
    </>
  );
}

export default App;
