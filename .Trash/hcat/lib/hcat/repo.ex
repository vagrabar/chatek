defmodule Hcat.Repo do
  use Ecto.Repo,
    otp_app: :hcat,
    adapter: Ecto.Adapters.Postgres
end
