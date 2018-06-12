# Changelog

# 1.3.0

- Support overriding libgraphqlparser install location (use `--with-graphqlparser-xxx` options to override) #29

# 1.2.0

- Support `tracer:` keyword to `.parse` (supports GraphQL::Tracing) #27

# 1.1.0

- Support `null`

# 1.0.0

- No changes

# 0.5.2

- Specify dependency of GraphQL < 1.0.0

# 0.5.1

- Fix strings with a null byte but no newline character #16

# 0.5.0

- Support `libgraphqlparser` 0.5.0 (but not 0.4.0)

# 0.4.0

- Raise a `ParseError` when the query string contains a null byte

# 0.3.0

- Fix inline fragments without type conditions

# 0.2.3

- Fix graphql version lock

# 0.2.2

- Use a stack variable for the AST node instead of putting it on the heap

# 0.2.1

- Use Ruby's `StringValueCStr` to ensure that the string is null-terminated

# 0.2.0

- Search `/usr`, `/usr/local`, or `--with-graphql-*` for installed `libgraphqlparser`
