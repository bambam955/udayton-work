# cps449-microservice1

This microservice provides a REST API for calculating Latin honors guidance from GPA and credit hours.

- `GET /honors/:gpa?credits=<credits>` returns an honors classification and advisory output.
- `POST /honors` accepts JSON body `{ "gpa": 3.85, "creditHours": 72 }`.
- Latin honors thresholds:
  - `Cum Laude`: GPA `>= 3.50` and `< 3.70` with at least `60` total credits.
  - `Magna Cum Laude`: GPA `>= 3.70` and `< 3.90` with at least `60` total credits.
  - `Summa Cum Laude`: GPA `>= 3.90` with at least `60` total credits.
- Credits are optional; when provided, results include stronger eligibility and risk context.
