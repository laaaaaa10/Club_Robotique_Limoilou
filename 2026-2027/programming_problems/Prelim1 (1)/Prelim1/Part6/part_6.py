from __future__ import annotations  # imported for tests
import difflib                      # imported for tests
import time                         # imported for tests
import traceback                    # imported for tests


def solve(cookies: list[tuple[float, float, float]]) -> bool:
    """
    Return True when no two cookies overlap or touch, otherwise False.
    / Retourne True si aucun biscuit ne se chevauche ni ne se touche, sinon
    False.

    Parameters / Paramètres:
        cookies (list[tuple[float, float, float]]): (x, y, radius) of every
                cookie / (x, y, rayon) de chaque biscuit

    Returns / Retour:
        bool: True if the layout is valid / True si la disposition est valide
    """
    answer = True   # starter value / valeur de départ
    ### YOUR CODE GOES HERE ###
    ### VOTRE CODE VA ICI ###


    return answer


# #############################################################################
#  TEST RIG - DO NOT MODIFY · NE PAS MODIFIER (below this line / sous cette ligne)
# #############################################################################
#  Each test is a dictionary / Chaque test est un dictionnaire :
#      "label"     : text printed next to the result (str)
#      "args"      : inputs, in order, e.g. (cookies,)
#      "expected"  : the value solve() must return
#  Tip for the solution / Astuce pour la solution : the distance between two
#  cookies is sqrt((x1-x2)^2 + (y1-y2)^2); it must be STRICTLY greater than
#  r1 + r2. / la distance entre deux biscuits vaut sqrt((x1-x2)^2 + (y1-y2)^2);
#  elle doit être STRICTEMENT supérieure à r1 + r2.
# #############################################################################

def main():
    run_tests(solve, TESTS, title="Part 6")

TESTS = [
    {
        "label": "Example 1 (only one cookie)",
        "args": ([(2, 3, 3)],),
        "expected": True,
    },
    {
        "label": "Example 2 (two separate cookies)",
        "args": ([(2, 3, 3), (5, 7, 1)],),
        "expected": True,
    },
    {
        "label": "Example 3 (first and third cookies touching)",
        "args": ([(2, 3, 3), (5, 7, 1), (2, 8, 2)],),
        "expected": False,
    },
    {
        "label": "Example 4 (second and third cookies overlapping)",
        "args": ([(2, 3, 3), (5, 7, 1), (9, 10, 5)],),
        "expected": False,
    },
]

# ---------------------------------------------------------------------------
#  TEST ENGINE - standard library only (nothing to install)
#  MOTEUR DE TESTS - uniquement la bibliothèque standard (rien à installer)
# ---------------------------------------------------------------------------

DEFAULT_TOLERANCE = 1e-6        # max accepted difference between two floats
STOP_ON_FIRST_FAILURE = False   # True -> stop the run at the first failure
BAR = "=" * 68


def _kind(value):
    """Simple type name used in the reports (bool before int, on purpose)."""
    if isinstance(value, bool):
        return "bool"
    if isinstance(value, int):
        return "int"
    if isinstance(value, float):
        return "float"
    if isinstance(value, str):
        return "str"
    if isinstance(value, list):
        return "list"
    if isinstance(value, tuple):
        return "tuple"
    return type(value).__name__


def _describe(value):
    """Short description such as 'list[str] of length 5' or 'float'."""
    if isinstance(value, (list, tuple)):
        inner = f"[{_kind(value[0])}]" if len(value) > 0 else ""
        return f"{_kind(value)}{inner} of length {len(value)}"
    return _kind(value)


def _format(value, indent=""):
    """Pretty-print a value; a list is printed one element per line."""
    if not isinstance(value, (list, tuple)):
        return repr(value)
    if len(value) == 0:
        return "[]"
    opening, closing = ("[", "]") if isinstance(value, list) else ("(", ")")
    child = indent + "    "
    body = ",\n".join(child + _format(item, child) for item in value)
    return f"{opening}\n{body}\n{indent}{closing}"


def _indent(text, width):
    """Indent every line of text by 'width' spaces."""
    pad = " " * width
    return "\n".join(pad + line for line in str(text).splitlines())


def _string_diff(expected, actual):
    """Explain precisely where two strings differ, with a caret."""
    limit = min(len(expected), len(actual))
    index = 0
    while index < limit and expected[index] == actual[index]:
        index += 1
    pad = " " * len("expected ")
    lines = [
        f"expected {expected!r} (length {len(expected)})",
        f"got      {actual!r} (length {len(actual)})",
    ]
    if index < limit:
        lines.append(pad + " " * (index + 1) + "^")
        lines.append(
            pad
            + f"first difference at character {index}: "
            + f"expected {expected[index]!r} but got {actual[index]!r}"
        )
    else:
        lines.append(
            pad
            + f"the first {limit} characters are identical, "
            + f"only the character count differs"
        )
    return "\n".join(lines)


def compare(expected, actual, path="answer", tolerance=DEFAULT_TOLERANCE,
            decimals=None, diffs=None):
    """Recursively collect every difference between expected and actual.

    Works for scalars (int, float, bool, str) and for lists / tuples of
    scalars, including nested lists such as a 2D grid. Floats are compared
    with a tolerance (or with 'decimals'), never with ==.
    """
    if diffs is None:
        diffs = []

    # --- sequences (list / tuple, possibly nested) --------------------------
    if isinstance(expected, (list, tuple)) and isinstance(actual, (list, tuple)):
        for index in range(min(len(expected), len(actual))):
            compare(expected[index], actual[index], f"{path}[{index}]",
                    tolerance, decimals, diffs)
        if len(expected) > len(actual):
            diffs.append(
                f"{path}: expected {_describe(expected)} but got "
                f"{_describe(actual)} "
                f"({len(expected) - len(actual)} element(s) are missing)"
            )
        elif len(actual) > len(expected):
            diffs.append(
                f"{path}: expected {_describe(expected)} but got "
                f"{_describe(actual)} "
                f"({len(actual) - len(expected)} element(s) too many)"
            )
        return diffs

    if isinstance(expected, (list, tuple)) or isinstance(actual, (list, tuple)):
        diffs.append(
            f"{path}: expected {_describe(expected)} but got {_describe(actual)}"
        )
        return diffs

    # --- strings ------------------------------------------------------------
    if isinstance(expected, str) and isinstance(actual, str):
        if expected != actual:
            diffs.append(
                f"{path}: strings differ\n{_indent(_string_diff(expected, actual), 4)}"
            )
        return diffs

    if isinstance(expected, str) or isinstance(actual, str):
        diffs.append(
            f"{path}: expected {_describe(expected)} {expected!r} "
            f"but got {_describe(actual)} {actual!r}"
        )
        return diffs

    # --- booleans (checked before int, because True == 1) -------------------
    if isinstance(expected, bool) or isinstance(actual, bool):
        if not isinstance(expected, bool) or not isinstance(actual, bool):
            diffs.append(
                f"{path}: expected {_describe(expected)} {expected!r} "
                f"but got {_describe(actual)} {actual!r}"
            )
        elif expected != actual:
            diffs.append(f"{path}: expected {expected!r} but got {actual!r}")
        return diffs
    # --- numbers ------------------------------------------------------------
    if isinstance(expected, (int, float)) and isinstance(actual, (int, float)):
        difference = abs(float(expected) - float(actual))
        if decimals is not None:
            limit = 0.5 * (10 ** -decimals)
            note = f"compared with {decimals} decimals (max accepted difference {limit})"
        elif isinstance(expected, int) and isinstance(actual, int):
            limit = 0.5
            note = "compared as integers"
        else:
            limit = tolerance
            note = f"compared with a tolerance of {tolerance:g}"
        if difference > limit:
            diffs.append(
                f"{path}: expected {expected!r} but got {actual!r} "
                f"(difference {difference:.6g}; {note})"
            )
        return diffs

    # --- everything else (None, dict, set, dataclass, custom objects, ...) --
    if expected != actual:
        diffs.append(
            f"{path}: expected {_describe(expected)} {expected!r} "
            f"but got {_describe(actual)} {actual!r}"
        )
    return diffs


def _visual_diff(expected, actual):
    """Line-by-line diff, only when both values are lists of strings."""
    if not (isinstance(expected, list) and isinstance(actual, list)):
        return []
    if not all(isinstance(item, str) for item in expected + actual):
        return []
    return list(
        difflib.unified_diff(
            list(expected),
            list(actual),
            fromfile="expected",
            tofile="your answer",
            lineterm="",
            n=1,
        )
    )


def _inputs_of(test):
    """Text describing the arguments given to the tested function."""
    parts = [repr(arg) for arg in test.get("args", ())]
    parts += [f"{name} = {value!r}" for name, value in test.get("kwargs", {}).items()]
    if not parts:
        return "<no input>"
    return "\n".join(parts)
def run_tests(function, tests, title="Tests"):
    """Run every test, then print one report with all the differences.

    No test stops the others: an exception is reported as an error and the run
    continues. For every failure the report repeats: the test number, the
    input, the expected value, the returned value and the exact difference(s).
    """
    results = []
    print(BAR)
    print(f"  TESTS - {title}")
    print(f"  {len(tests)} test(s) / test(s)")
    print(BAR)

    for number, test in enumerate(tests, start=1):
        label = test.get("label", "")
        actual, error = None, None
        start = time.perf_counter()
        try:
            actual = function(*test.get("args", ()), **test.get("kwargs", {}))
        except Exception:
            error = traceback.format_exc()
        elapsed = (time.perf_counter() - start) * 1000.0

        expected = test.get("expected")
        if error is not None:
            status, diffs = "ERROR", []
        else:
            diffs = compare(
                expected,
                actual,
                tolerance=test.get("tolerance", DEFAULT_TOLERANCE),
                decimals=test.get("decimals"),
            )
            status = "PASSED" if not diffs else "FAILED"

        results.append(
            {
                "number": number,
                "label": label,
                "test": test,
                "status": status,
                "expected": expected,
                "actual": actual,
                "error": error,
                "diffs": diffs,
            }
        )
        print(f"  Test #{number:<2} {status:<7} {label}   ({elapsed:.1f} ms)")
        if STOP_ON_FIRST_FAILURE and status != "PASSED":
            break

    passed = sum(1 for r in results if r["status"] == "PASSED")
    failed = sum(1 for r in results if r["status"] == "FAILED")
    errors = sum(1 for r in results if r["status"] == "ERROR")
    print("-" * 68)
    print(
        f"  RESULTS: {passed} passed | {failed} failed | {errors} error(s)   "
        f"({len(results)} test(s) run)"
    )

    broken = [r for r in results if r["status"] != "PASSED"]
    if not broken:
        print(BAR)
        print("  Your answer is valid congratulations!!")
        print("  Votre réponse est valide, félicitations!!")
        print(BAR)
        return results

    print(BAR)
    print("  DETAILS ON THE FAILURES / DÉTAILS DES ÉCHECS")
    print(BAR)
    for r in broken:
        print(f"  Test #{r['number']} - {r['label']}   [{r['status']}]")
        inputs = _inputs_of(r["test"]).split("\n")
        print(f"  Inputs   : {inputs[0]}")
        for line in inputs[1:]:
            print(f"             {line}")
        print(f"  Expected : {_describe(r['expected'])}")
        print(_indent(_format(r["expected"]), 8))
        if r["error"] is not None:
            print("  Returned : an exception was raised by your code")
            print("             une exception a été levée par votre code")
            print(_indent("\n".join(r["error"].strip().splitlines()[-6:]), 8))
        else:
            print(f"  Returned : {_describe(r['actual'])}")
            print(_indent(_format(r["actual"]), 8))
            print(f"  Differences ({len(r['diffs'])}):")
            for diff in r["diffs"]:
                lines = diff.split("\n")
                print(_indent("- " + lines[0], 6))
                for line in lines[1:]:
                    print(_indent("  " + line, 6))
            visual = _visual_diff(r["expected"], r["actual"])
            if visual:
                print("  Line-by-line diff / Diff ligne par ligne (expected -> your answer):")
                print(_indent("\n".join(visual), 6))
        print("-" * 68)

    print(BAR)
    print("  Your answer is invalid!")
    print("  Votre réponse est invalide!")
    print(BAR)
    return results

if __name__ == "__main__":
    # ----
    #  When this file is run directly (Play button ▶, or `python file.py`),
    #  Python sets __name__ to "__main__" and the tests start right away.
    #  Quand ce fichier est exécuté directement (bouton Play ▶ ou
    #  `python fichier.py`), Python met __name__ à "__main__" et les tests
    #  démarrent immédiatement.
    # ----
    main()

