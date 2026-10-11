# CS166 · Databases

The [mechanic-shop project](mechanic-shop-db/README.md) retains both phases, ERDPlus diagram, SQL schemas/indexes, Java CLI and Swing GUI, six dummy-data CSVs, JDBC driver, and historical scripts. [Phase 1](mechanic-shop-db/phase1/README.md) and [Phase 2](mechanic-shop-db/phase2/README.md) preserve their documentation. [Local notes](notes/) add course/lab/exam reference summaries.

Run commands from `courses/cs166/mechanic-shop-db/phase2`. The actual script paths are `scripts/start.sh` and `scripts/deploy_ucr.sh`; the original root README's `phase2/deploy_ucr.sh` mention is stale.

## Compile without creating output in the archive

```bash
export COURSEWORK_BUILD_DIR="$HOME/GoalRuns/ucr-coursework-builds/cs166-java"
mkdir -p "$COURSEWORK_BUILD_DIR"
cd courses/cs166/mechanic-shop-db/phase2/java
javac -cp 'lib/*' src/MechanicShop.java src/MechanicShopGUI.java -d "$COURSEWORK_BUILD_DIR"
```

On the checked Mac, the default `javac` shim had no configured runtime, while `/opt/homebrew/opt/openjdk/bin/javac` (26.0.1) compiled both sources. Use a working JDK; the original compile/run scripts also look for `/opt/homebrew/opt/openjdk`.

After setting up your own disposable PostgreSQL database and loading the retained schema/data, the CLI can run from that same `java` cwd:

```bash
java -cp "lib/*:$COURSEWORK_BUILD_DIR" MechanicShop <dbname> <port> <user>
```

For local GUI setup, the historical `bash scripts/start.sh <dbname> <port> <user>` command from `phase2` checks/starts a Homebrew PostgreSQL service, **drops/recreates the named database**, loads the CSVs, writes `java/bin/` and launches Swing. Choose a disposable database. `bash scripts/deploy_ucr.sh <netid>` uploads/runs on the course server and requires a UCR NetID. These original service/deployment workflows were not exercised in consolidation; PostgreSQL was absent on the checked host and no learner account was used.

Both Java sources compile, all nine shell scripts parse, and retained CSV row counts are customer=500, mechanic=250, car=800, owns=800, service_request=1500, closed_request=1000. These are dummy assignment resources and are retained even though they were generated historically. Counts and compilation do not prove SQL constraints, query results, write paths, or GUI behavior. No PostgreSQL/JDBC runtime, UCR server, data regeneration, or Swing interaction was tested. Preserve the original schema/validation and concurrency limitations.
