import React from "react";
import { AppBar, Toolbar, Typography, makeStyles } from "@material-ui/core";
import PanToolIcon from "@material-ui/icons/PanToolTwoTone";

const useStyles = makeStyles(theme => ({
  title: {
    marginLeft: theme.spacing(2)
  }
}));

function Header() {
  const classes = useStyles();
  return (
    <AppBar position="fixed">
      <Toolbar>
        <PanToolIcon />
        <Typography className={classes.title} varaint="h6" component="h1">
          Zero Contact Record Entry System
        </Typography>
      </Toolbar>
    </AppBar>
  );
}
export default Header;
