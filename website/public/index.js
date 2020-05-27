const messages = [];

// define variables that reference elements on our page
const messageForm = document.forms[0];
const messageInput = messageForm.elements["message"];
const messageList = document.getElementById("messages");
const clearButton = document.querySelector("#clear-messages");

// request the messages from our app's sqlite database
fetch("/messages", {})
  .then(res => res.json())
  .then(response => {
    response.forEach(row => {
      appendNewMessage(row.message);
      console.log(row.message);
    });
  });

// a helper function that creates a list item for a given message
const appendNewMessage = (message) => {
  const newListItem = document.createElement("li");
  newListItem.innerText = message;
  messageList.appendChild(newListItem);
};

// listen for the form to be submitted and add a new message when it is
messageForm.onsubmit = event => {
  // stop our form submission from refreshing the page
  event.preventDefault();

  const data = { message: messageInput.value };

  fetch("/message", {
    method: "POST",
    body: JSON.stringify(data),
    headers: { "Content-Type": "application/json" }
  })

  messages.push(messageInput.value);
  appendNewMessage(messageInput.value);

  // reset form
  messageInput.value = "";
  messageInput.focus();
};

clearButton.addEventListener("click", event => {
  fetch("/clear", {
    method: "DELETE"
  });
  messageList.innerHTML = "";
});
