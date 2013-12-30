import QtQuick 2.0

ListModel {
    id: messageModel

    function toHtml() {
        var result = "<table width='100%'>"
        for (var i = 0; i < messageModel.count; i++)
        {
            var item = messageModel.get(i)

            result += "<tr width='100%'> \
                    <td width='200px' align='right' style='padding: 5px; color: #aaa;'><nobr>" + item.sender + "</nobr></td> \
                    <td width='100%' style='padding: 5px'>" + item.message + "</td> \
                    <td width='100px' style='padding: 5px; color: #aaa;'>" + item.time + "</td> \
                    </tr>"
        }
        result += "</table>"
        return result
    }
}
