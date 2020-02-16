defmodule Chat1Web.PageController do
  use Chat1Web, :controller

  def index(conn, _params) do
    render(conn, "index.html")
  end
end
