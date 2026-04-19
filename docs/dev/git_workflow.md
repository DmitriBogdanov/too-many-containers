# Git workflow

## Branches

| Branch     | Description                 |
| ---------- | --------------------------- |
| `master`   | Stable releases             |
| `dev`      | Unstable development branch |
| `gh-pages` | GitHub Pages support branch |

## Commit messages

### Template

Commit messages should follow [conventional commits](https://www.conventionalcommits.org/en/v1.0.0/) template:

```
<type>: <Single line description below 80 characters>

<Multi-line description detailing all changes>
```

Where `<type>` is one of the following:

```
fix
feat
build
chore
ci
docs
refactor
perf
test
BREAKING CHANGE
```

> [!Note]
> Commit messages should be written in **imperative form**, see [examples](#examples).

> [!Important]
> All commits that affect code should be reflected by library [SEMVER](https://semver.org/).

### Examples

```
feat: Implement `tmc::hash`.

Implement transparent hashing with `tmc::hash`.
```

```
BREAKING CHANGE: Remove pointer stability requirement from `tmc::map`.

Remove pointer stability requirement from `tmc::map` to allow segmented b-tree implementation instead of node-based red-black tree.
```

```
ci: Fix FreeBSD test runners.

Fix incorrect VM launch directory for FreeBSD test runners.
```
