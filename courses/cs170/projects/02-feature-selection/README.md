## Running from this collection

From the collection root, enter `projects/02-feature-selection`, then use the original commands below. The CLI and supplied script checks use only the Python standard library (checked with Python 3.12). All three original dataset files are included locally; no download or account is needed. Their contents and filenames are unchanged. The original repository provides no further origin/license details for those datasets.

The supplied LOOCV script prints 91% for small-dataset features `{3, 5, 7}` against a historical 89% expectation; it reports that diagnostic but exits successfully. Its expected value and algorithm are preserved.

---

# Feature Selection

Project 2 for CS 170, Introduction to AI, at UC Riverside.

The program finds the best subset of features for a nearest neighbor classifier. It searches with two greedy algorithms:

- **Forward selection** starts with no features and adds the one that helps most, one at a time.
- **Backward elimination** starts with all features and removes the one that hurts least, one at a time.

Each candidate subset is scored by leave-one-out cross validation. The classifier is k-nearest-neighbor with Euclidean distance and a majority vote. Features are min-max normalized before the search.

## Run

From this project directory:

```bash
python3 src/main.py
```

The program asks for a data file name, then for an algorithm:

1. Forward selection
2. Backward elimination
3. KNN analysis, which runs both algorithms at k = 1, 3, 5, and 7

Type only the file name. The program looks in `data/`. For example, `small-test-dataset.txt`.

## Data

Each row is one instance. The first column is the class label. The rest are features, in a space separated list.

| File                     | Instances | Features |
| ------------------------ | --------- | -------- |
| `small-test-dataset.txt` | 100       | 10       |
| `large-test-dataset.txt` | 1000      | 40       |
| `titanic-clean.txt`      | 714       | 6        |

## Results

With k = 1, both algorithms agree on every dataset tested:

| Dataset                  | Best subset | Accuracy |
| ------------------------ | ----------- | -------- |
| `small-test-dataset.txt` | {3, 5}      | 92.0%    |
| `titanic-clean.txt`      | {2}         | 78.0%    |

Only 2 of the 10 features in the small dataset carry signal. The other 8 are noise, and adding them lowers accuracy. This is the point of the project: a nearest neighbor classifier weighs every feature equally, so irrelevant features move points apart in the wrong directions and the accuracy falls.

Both searches are greedy, so neither is guaranteed to find the true best subset. They agree here because the useful features are strong and few.

## Cost

The search is slow. Forward selection evaluates about n²/2 feature subsets, and each subset runs leave-one-out cross validation over every instance. On `small-test-dataset.txt` this takes seconds. On `large-test-dataset.txt`, with 1000 instances and 40 features, a single run did not finish in 15 minutes.

## Tests

Run from this project directory. The tests import modules two ways, so `src` must be on the path:

```bash
PYTHONPATH=src python3 tests/test_nn_classifier.py
PYTHONPATH=src python3 tests/test_loocv_validator.py
PYTHONPATH=src python3 tests/test_data_utils.py
PYTHONPATH=src python3 tests/test_knn_titanic.py
```

`test_knn_titanic.py` runs a full forward selection at four values of k. It takes several minutes.
