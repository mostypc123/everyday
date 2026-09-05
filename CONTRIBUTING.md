# Contributing guide

All contributions are welcome! Even though this is a personal tool I thought maybe someone will want to contribute.

## Code style

Please use 2 space tabs and make EVERY line max 80 chars (unless you're editing docs). Use the K&R style.

Do not use `int` nor `bool` for booleans. Use `_Bool`, so there is no unnecessary include.

We do not use `-Werror` because it can be annoying to make WIP code with, but your code must compile with it.

Use `#pragma once` for header guards.

For everything, use snake case. For macros, use screaming snake case.

## Commit messages

Use Conventional Commits: https://www.conventionalcommits.org/en/v1.0.0/
If you are making a WIP project, you do not have to, but the PR title MUST follow Conventional Commits either way.

## Reporting bugs

Submit a Github Issue: https://github.com/mostypc123/everyday/issues/new/.
According to context, use Conventional Commits-like titles.

