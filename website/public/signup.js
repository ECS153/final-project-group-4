const signupForm = document.forms[0];

// listen for the form to be submitted and add a new message when it is
signupForm.onsubmit = async event => {
  event.preventDefault();

  const username = signupForm.elements["username"].value;
  const password = signupForm.elements["password"].value;
  const password2 = signupForm.elements["password2"].value;

  if (password !== password2) {
    alert("Your passwords do not match, please try again.");
    return;
  }

  const data = {
    username: username,
    password: password
  };

  fetch("/signup", {
    method: "POST",
    body: JSON.stringify(data),
    headers: { "Content-Type": "application/json" }
  })
    .then(response => response.json())
    .then(data => {
      if (data.error) {
        alert(data.message);
      } else {
        window.location = "/";
      }
    })
    .catch(error => {
      console.error("Error:", error);
    });
};
