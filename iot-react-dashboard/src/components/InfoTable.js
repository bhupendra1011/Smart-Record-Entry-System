import React, { useState, useEffect } from "react";
import MaterialTable from "material-table";
import { CircularProgress } from "@material-ui/core";

function InfoTable() {
  let loading = false;
  const [datafeed, setDataFeed] = useState([]);
  const url =
    "https://api.thingspeak.com/channels/1029377/feeds.json?results=5;";

  const formatResponse = data => {
    return data.map(record => {
      const d = new Date(record.created_at);
      return {
        date: d.toLocaleDateString(),
        name: record.field2,
        meal: record.field3,
        time: d.toLocaleTimeString(),
        id: record.entry_id
      };
    });
  };

  async function getDetails() {
    const response = await fetch(url);
    const data = await response.json();
    // check if new entry is made then only update state;
    const last_entry = data.channel.last_entry_id;
    loading = false;
    setDataFeed(prevData => {
      const last_entry_record = prevData.length
        ? prevData[prevData.length - 1].id
        : -1;
      if (last_entry === last_entry_record && prevData.length !== 0) {
        return prevData;
      } else {
        const formattedData = formatResponse(data.feeds);
        const latestFeeds = formattedData.filter(
          item => item.id > last_entry_record
        );
        console.log(latestFeeds);
        return [...prevData, ...latestFeeds];
      }
    });
  }

  useEffect(() => {
    getDetails();
    const timer = setInterval(() => {
      getDetails();
    }, 2000);
    return () => clearInterval(timer);
  }, []);

  if (loading) {
    return (
      <div
        style={{
          display: "flex",
          flexDirection: "column",
          alignItems: "center",
          marginTop: 50
        }}
      >
        <CircularProgress />
      </div>
    );
  }
  return (
    <MaterialTable
      title="Cafeteria Records Preview"
      columns={[
        { title: "Date", field: "date" },
        { title: "Name", field: "name" },
        { title: "Meal", field: "meal" },
        { title: "Time", field: "time" }
      ]}
      data={datafeed}
    />
  );
}
export default InfoTable;
