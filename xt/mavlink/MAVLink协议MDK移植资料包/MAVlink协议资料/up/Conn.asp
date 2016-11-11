<%
Set rs=server.createobject("adodb.recordset")
Set Conn=server.createobject("adodb.connection")
DBPath = Server.MapPath("abc.mdb")
Conn.Open "driver={Microsoft Access Driver (*.mdb)};dbq=" & DBPath
%>


