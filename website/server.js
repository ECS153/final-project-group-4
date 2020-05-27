const express = require("express");
const bodyParser = require("body-parser");
const cookieSession = require("cookie-session");
const fs = require("fs");
var sha1 = require("sha1");
const sqlite3 = require("sqlite3").verbose();

const app = express();
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());
app.use(express.static("public"));
app.use(
  cookieSession({
    name: "session",
    keys: [process.env.COOKIE_SIGNING_KEY],

    // Cookie Options
    maxAge: 24 * 60 * 60 * 1000 // 24 hours
  })
);

function randomString(len) {
  const chars =
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  let result = "";

  for (let i = 0; i < len; i++) {
    result += chars[Math.floor(Math.random() * chars.length)];
  }

  return result;
}

const db = new sqlite3.Database(
  "./ecs153final.db",
  sqlite3.OPEN_READWRITE | sqlite3.OPEN_CREATE,
  err => {
    if (err) {
      console.error(err.message);
      return;
    }
  }
);

// create tables if they don't exist
db.serialize(() => {
  db.run(`create table if not exists user (
            id integer primary key autoincrement,
            username text not null,
            password_hash text not null
          )`);

  db.run(`create table if not exists messages (
            id integer primary key autoincrement,
            message text not null
          )`);
});

app.get("/", (request, response) => {
  if (request.session.isNew) {
    response.sendFile(`${__dirname}/views/login.html`);
  } else {
    response.sendFile(`${__dirname}/views/index.html`);
  }
});

app.post("/login", (request, response) => {
  const username = request.body.username;
  const password_hash = sha1(request.body.password);

  db.serialize(() => {
    db.get(
      `select id, username, password_hash from user where username = '${username}'`
    ),
      (err, row) => {
        console.log("weoiufnweiofn");
        if (err || row === undefined) {
          console.log(err);
          response
            .status(500)
            .json({ error: true, message: "internal server error" });
        } else if (row.password_hash !== password_hash) {
          response
            .status(401)
            .json({ error: true, message: "invalid credentials" });
        } else {
          request.session.id = row.id;
          response.json({ error: false });
        }
      };
  });
});

app.get("/signup", (request, response) => {
  response.sendFile(`${__dirname}/views/signup.html`);
});

app.post("/signup", (request, response) => {
  const json = JSON.parse(request.body);

  const username = json.username;
  const password = json.password;
  const password_hash = sha1(password);

  db.serialize(() => {
    db.get(
      `select count(*) as count from user where username = '${username}'`,
      (err, row) => {
        if (err || row === undefined) {
          console.log(err);
          response
            .status(500)
            .json({ error: true, message: "internal server error" });
        } else if (row.count === 0) {
          db.run(
            `insert into user (username, password_hash) values ('${username}', '${password_hash}')`
          );
          response.json({
            error: false
          });
        } else {
          response.status(401).json({
            error: true,
            message: "username already exists, please choose another one"
          });
        }
      }
    );
  });
});

// endpoint to get all the messages in the database
app.get("/messages", (request, response) => {
  db.all("select * from messages", (err, rows) => {
    response.json(rows);
  });
});

app.post("/message", (request, response) => {
  db.serialize(() => {
    const cleaned = cleanseString(request.body.message);
    db.run(`insert into messages (message) VALUES (?)`, cleaned, error => {
      if (error) {
        response.json({ message: "error!" });
      } else {
        response.json({ message: "success" });
      }
    });
  });
});

app.delete("/messages", (request, response) => {
  db.serialize(() => {
    db.run("truncate table messages");
  });
});

// helper function that prevents html/css/script malice
const cleanseString = function(string) {
  return string.replace(/</g, "&lt;").replace(/>/g, "&gt;");
};

// listen for requests :)
var listener = app.listen(process.env.PORT, () => {
  console.log(`Your app is listening on port ${listener.address().port}`);
});
