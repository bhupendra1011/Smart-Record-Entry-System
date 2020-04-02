import React from "react";
import Header from "./components/Header";
import InfoTable from "./components/InfoTable";
import IOTComponents from "./components/IOTComponents";
import { Grid, useMediaQuery } from "@material-ui/core";

function App() {
  const greatherThanSmall = useMediaQuery(theme => theme.breakpoints.up("sm"));
  return (
    <>
      <Header />
      <Grid
        container
        spacing={3}
        style={{ paddingTop: greatherThanSmall ? 80 : 20 }}
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
