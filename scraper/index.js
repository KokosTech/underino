const axios = require("axios");
const cheerio = require("cheerio");
const express = require("express");
const { rateLimit } = require("express-rate-limit");
const limiter = rateLimit({
  windowMs: 15 * 60 * 1000, // 15 minutes
  limit: 20, // Limit each IP to 60 requests per `window` (here, per 15 minutes)
  standardHeaders: true, // Return rate limit info in the `RateLimit-*` headers
  legacyHeaders: false, // Disable the `X-RateLimit-*` headers
});

const app = express();
app.use(limiter); // Apply the rate limiting middleware
app.use(express.json()); // Parse JSON bodies

const port = 3000;

const url = "https://www.metrosofia.com/bg/schedule/beli-dunav";

app.get("/", async (req, res) => {
  const timetables = await getTimetables(url);
  res.json({
    // date now - only date without time
    date: new Date().toISOString().split("T")[0],
    ...timetables,
  });
});

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`);
});

const getTimetables = async (url) => {
  let obelya = [];
  let vitosha = [];

  try {
    const response = await axios.get(url);
    const $ = cheerio.load(response.data);

    $(".is-hidden-touch table").each((index, element) => {
      $(element)
        .find("tr td")
        .each((i, row) => {
          const words = $(row).text().trim().replace(/\s+/g, " ").split(" ");
          const cleanWords = words.filter((item) => item !== "");

          if (index === 0) {
            obelya.push(...cleanWords);
          } else {
            vitosha.push(...cleanWords);
          }
        });
    });

    console.log("Obelya:", obelya);
    console.log("Vitosha:", vitosha);
  } catch (error) {
    console.error("Error fetching data:", error);
  }

  return {
    obelya,
    vitosha,
  };
};
