defmodule HcatWeb.PageController do
  use HcatWeb, :controller

  def index(conn, _params) do
    render(conn, "index.html")
  end
end
