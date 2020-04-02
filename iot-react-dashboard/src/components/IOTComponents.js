import React from "react";
import {
  makeStyles,
  Card,
  CardContent,
  CardMedia,
  Typography
} from "@material-ui/core";

const useStyles = makeStyles(theme => ({
  container: {
    margin: theme.spacing(3)
  },
  moduleInfoContainer: {
    display: "flex",
    alignItems: "center"
  },
  moduleInfo: {
    width: "100%",
    display: "flex",
    justifyContent: "space-between"
  },
  thumbnail: {
    objectFit: "cover",
    width: 200,
    height: 180
  }
}));

function IOTComponents() {
  const modules = [
    {
      name: "NODEMCU - ESP8266",
      info:
        "The NodeMCU Wifi Board is an all-in-one microcontroller + WiFi platform",
      thumbnail:
        "https://www.electronicscomp.com/image/cache/catalog/nodemcu-esp8266-wifi-board-cp2102-ic-based-228x228.jpg"
    },
    {
      name: "OLED",
      info:
        "0.96 inch OLED Display Module can be interfaced with any microcontroller",
      thumbnail:
        "https://www.electronicscomp.com/image/cache/catalog/oled-module-6-pin-0.96-inch-228x228.JPG"
    },
    {
      name: "RC522 - RFID Reader",
      info:
        "RC522 - RFID Reader / Writer 13.56MHz,uses SPI to communicate with microcontrollers.  ",
      thumbnail:
        "https://www.electronicscomp.com/image/cache/catalog/rc522-rfid-reader-writer-module-india-228x228.jpg"
    },
    {
      name: "RED LED - 2Pin",
      info:
        "It is a 3mm Red DIP LED. An LED is a two-lead semiconductor light source, which emits lights when activated. ",
      thumbnail:
        "https://robu.in/wp-content/uploads/2019/10/3mm-Green-DIP-LED-3.jpg"
    }
  ];

  return (
    <div>
      {modules.map((module, index) => (
        <IOTComponent key={index} module={module} />
      ))}
    </div>
  );
}

function IOTComponent({ module }) {
  const classes = useStyles();
  const { name, info, thumbnail } = module;
  return (
    <Card className={classes.container}>
      <div className={classes.moduleInfoContainer}>
        <CardMedia image={thumbnail} className={classes.thumbnail} />
        <div className={classes.moduleInfo}>
          <CardContent>
            <Typography gutterBottom variant="h5" component="h2">
              {name}
            </Typography>
            <Typography
              gutterBottom
              variant="body1"
              component="p"
              color="textSecondary"
            >
              {info}
            </Typography>
          </CardContent>
        </div>
      </div>
    </Card>
  );
}
export default IOTComponents;
