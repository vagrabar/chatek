# This file is responsible for configuring your application
# and its dependencies with the aid of the Mix.Config module.
#
# This configuration file is loaded before any dependency and
# is restricted to this project.

# General application configuration
use Mix.Config

config :chat1,
  ecto_repos: [Chat1.Repo]

# Configures the endpoint
config :chat1, Chat1Web.Endpoint,
  url: [host: "localhost"],
  secret_key_base: "WHVTxEI3drXDH8ZDPdfEoAcpqiTto/6Exdab2ddAV1miqznn6EpOu6IEUR7yergU",
  render_errors: [view: Chat1Web.ErrorView, accepts: ~w(html json)],
  pubsub: [name: Chat1.PubSub, adapter: Phoenix.PubSub.PG2],
  live_view: [signing_salt: "PwrTH8ov"]

# Configures Elixir's Logger
config :logger, :console,
  format: "$time $metadata[$level] $message\n",
  metadata: [:request_id]

# Use Jason for JSON parsing in Phoenix
config :phoenix, :json_library, Jason

# Import environment specific config. This must remain at the bottom
# of this file so it overrides the configuration defined above.
import_config "#{Mix.env()}.exs"
