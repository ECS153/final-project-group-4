const loginForm = document.forms[0];

// listen for the form to be submitted and add a new message when it is
loginForm.onsubmit = event => {
  event.preventDefault();

  const username = loginForm.elements["username"].value;
  const password = loginForm.elements["password"].value;

  const data = {
    username: username,
    password: password
  };

  fetch("/login", {
    method: "POST",
    body: JSON.stringify(data),
    headers: { "Content-Type": "application/json" }
  })
    .then(response => response.json())
    .then(data => {
      if (data.error) {
        alert(data.message);
      } else {
        window.location.reload();
      }
    }).catch(error => {
      console.error("Error:", error);
    });
};
