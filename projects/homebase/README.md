# HomeBase

A shared-home management team project with chores, expenses, households and notifications. This archive addition is explicitly authorized; no course number or assignment provenance has been established. The owned source is [mchen04/homebase](https://github.com/mchen04/homebase), a public fork of [freddysongg/homebase](https://github.com/freddysongg/homebase), captured at `21758cc0381ec3cef769d250d0e50091a3d46869`.

The [original root README](README.original.md) is byte-identical and credits Alex Yen, Freddy Song, Michael Chen, Brandon Sun and Tabito Sakamoto. The original [MIT license](LICENSE), copyright 2025 Freddy Song, is retained. All 144 current source files and their modes are preserved, including both lockfiles, backend tests, Cypress specs, icons and the 9.3 MB video. Only the original root README's location changes. This guide is archive-authored; it supplements the unchanged [backend README](backend/README.md).

## Working directories and installation

Keep `backend/` and `frontend/` intact: each is an independent npm package. Node 22.23.3 / npm 10.9.9 passed the supplied backend tests on macOS ARM64. The historical backend README asks for Node 18+; Node 26.3.1 fails two suites during legacy JWT dependency initialization. No runtime or package versions were changed in the source.

Use a scratch copy to keep dependencies, caches, `.next` output and Mongo test databases out of the archive. From this directory, with Node 22 available:

```bash
homebase_work=$(mktemp -d "${TMPDIR:-/tmp}/homebase-work.XXXXXX")
cp -R backend frontend "$homebase_work/"
export npm_config_cache="$homebase_work/npm-cache"
export CYPRESS_CACHE_FOLDER="$homebase_work/cypress-cache"
export MONGOMS_DOWNLOAD_DIR="$homebase_work/mongodb-cache"
export MONGOMS_DISABLE_POSTINSTALL=1
export NEXT_TELEMETRY_DISABLED=1
cd "$homebase_work/backend"
npm ci --no-audit --no-fund
cd "$homebase_work/frontend"
npm ci --legacy-peer-deps --no-audit --no-fund
```

The frontend's literal `npm ci` fails with `ERESOLVE`: locked `react-day-picker` 8.10.1 declares React 16–18 peers, while this project uses React 19. `--legacy-peer-deps` installs the unchanged lockfile; it does not resolve or repair that compatibility mismatch. Public package/Mongo/Cypress downloads require network access. No paid service or existing user account is needed for the supplied backend tests.

## Supplied checks and reachable startup

From the scratch copy:

```bash
cd "$homebase_work/backend"
npm test -- --runInBand
npm run lint
# Health/startup only: test mode skips database connection. Use an unused port.
NODE_ENV=test PORT=15001 npm start
# In another terminal: curl http://127.0.0.1:15001/
# Stop the server with Ctrl-C before continuing.

cd "$homebase_work/frontend"
npm run lint
npm run build
node node_modules/typescript/bin/tsc --noEmit --incremental false
npm run format:check
npm run dev -- --hostname 127.0.0.1 --port 13000
```

The original backend suite passes **9 suites / 38 tests** under Node 22 using real disposable MongoDB processes. Its setup clears test collections and shuts down those databases; email/push dependencies are mocked. Backend lint passes. Original `npm start` in test mode serves the API health JSON. This does not prove a persistent database connection or the full application.

Frontend lint and build exit 1 with existing Dashboard unused imports and `/homes` anchor-navigation errors; build compilation completes before lint stops it. Typecheck exits 2 with existing Next 15 route/async-params incompatibilities, implicit types, JWT/session and component type errors. Formatting check exits 1 for `src/components/usettings/Settings.tsx`. These failures are preserved. The original dev server returns HTTP 200 for `/` and `/login`, with Next route/component payloads. No browser hydration, visible login form, visual layout or authenticated UI flow was tested. Production `npm start` requires a successful build and was not exercised. Mutating format commands and watch modes were not run.

## Historical integration requirements and limits

For an independently owned disposable local integration environment, backend `src/config/db.js` reads **`MONGO_URI`**; `src/server.js` defaults to **5000**. Frontend login/signup and several API calls are hard-coded to **`http://localhost:5001`**, so such integration needs backend `PORT=5001`. The historical backend README's port 3001 and `MONGODB_URI` prerequisite are inconsistent with this backend code. The separate frontend NextAuth route does read **`MONGODB_URI`**, plus `NEXTAUTH_SECRET` and `NEXTAUTH_URL`; backend authentication reads `JWT_SECRET`. Supply only your own disposable configuration. No account or hosted database has been recreated.

The frontend NextAuth credentials route logs credentials/user data and compares a plain password; it coexists with the separate JWT/localStorage login path. Both remain historical source and were not exercised with user accounts. Email uses `SMTP_*` and `FRONTEND_URL`; optional push code uses `WEB_PUSH_CONTACT` and `VAPID_*`, and imports `web-push`, which is not a declared package dependency. That push module is not required by the measured API health startup; no live email/push delivery or payment/cloud integration is claimed.

Original Cypress specs can be invoked from `frontend/` with `npx cypress run`; they expect frontend port 3000, backend port 5001 and a seeded synthetic login user. They were retained but not run: that browser/account/database setup was not recreated. No personal services, accounts or open apps were used. The nested [frontend CI file](frontend/.github/workflows/ci.yaml) remains at its original internal path; it is not active as collection-root GitHub Actions CI.

See [archive validation](../../docs/VALIDATION.md), [attribution](../../ATTRIBUTION.md), [history/privacy](../../docs/HISTORY.md) and [omissions](../../docs/OMISSIONS.md). Exact command receipts and helper diagnostics are outside the checkout under `/Users/michaelchen/GoalRuns/ucr-coursework/t_55fd20c0/`. Existing coursework and Word Hunt are unchanged.
