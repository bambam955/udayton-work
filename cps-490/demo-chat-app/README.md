# demo-web-project

This is my work for the tutorials we are going through in class.

## Tutorial Completion Proof

<details><summary>Chapter 2</summary>

_Screenshot of the successful DB connection_

![screenshot of successful DB connection](./_assets/ch2/backend-db.png)

</details>

<details><summary>Chapter 3</summary>

_Screenshot of successful unit test run_

![screenshot of successful unit test run](./_assets/ch3/unit-tests.png)

_Screenshot of successful express API request_

![screenshot of successful express API request](./_assets/ch3/express-app-get-posts.png)

</details>

<details><summary>Chapter 4</summary>

_Screenshot of the successful post creation from the frontend_

![screenshot of creating post from frontend](./_assets/ch4/create-posts-frontend.png)

</details>

<details><summary>Chapter 5</summary>

_Screenshot of requiring a user to log in before creating posts_

![screenshot of requiring login before making posts](./_assets/ch5/login-to-create-posts.png)

_Screenshot of successfully creating an authenticated post_

![screenshot of creating authenticated post](./_assets/ch5/authenticated-post-created.png)

</details>

<details><summary>Chapter 6</summary>

_Screenshot showing a live chat between two users on the messaging platform_

![screenshot of users messaging back and forth](./_assets/ch6/live-messages.png)

</details>

## Production Release Notes

The production release is published from a separate Git repo by the following process:

```bash
npm i -g heroku

# Run from root of repo
cp -r production ../
git init
git add .
git commit -m "Initial commit"
heroku git:remote -a mooreb26-test1
git push heroku master
```

This is necessary because the Git repo pushed to Heroku must have all of the contents of the `production` folder at the root of the repo.
