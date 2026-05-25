# bambam955.bitbucket.io

Static website for my Bitbucket homepage.

Link: <https://bambam955.bitbucket.io>

## Deployment

Because this project is built with [Vite](https://vite.dev), I needed some way to build the project with Vite and then publish the artifact to Bitbucket Pages. Unfortunately, BB Pages doesn't have support for anything other than serving exactly what is in the default branch of the repository.

So, the solution was for development to live in a `source` branch, and then add a pipeline that builds the site and force-pushes the build artifacts to the `main` branch for deployment.
