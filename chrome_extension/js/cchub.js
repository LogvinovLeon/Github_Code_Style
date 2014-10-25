/**
 * Created by hubert on 25.10.14.
 */
"use strict";

$(function () {

    var url = window.location.href;

    console.log(url);

    var re = /.*github\.com\/([^\/]+)\/([^\/]+)\/pull\/([^/]+)\/.*/;
    var tokens = url.match(re);
    var user = tokens[1];
    var repo = tokens[2];
    var pull = tokens[3];

    console.log('KURWA', user, repo, pull);
    console.log(tokens);

    var requestUrl = "http://students.mimuw.edu.pl:8080/client/" + user + "/" + repo + "/" + pull;

    console.log(requestUrl);

    $.get(requestUrl)
        .done(function (result) {
            applyNotifications(result);
            setUpScrolbarHints();
        })
        .fail(function (errmsg) {
            alert(errmsg);
        });
});

function setUpScrolbarHints() {
    $('body').append('<div id="scrollbar-hint"></div>')
}

function applyNotifications(data) {
    console.log(data);
    var files = data.files;
    console.log(files);

    files.forEach(function (item) {
        item.notifications.forEach(function (notif) {
            var b = $('.blob-code b[data-path="' + item.filename + '"][data-line="' + notif.line + '"]');

            b.parent().parent().addClass('cchub-notification');

            b.parent()
                .append(
                    '<div class="cchub-more-btn">' +
                        '<div class="cchub-tooltip">' + notif.content + '</div>' +
                    '</div>'
            );

            //var top =
            //$('#scrollbar-hint').append('<div class="item" style="' + top + '"></div>')

            notif.type.forEach(function (type) {
                b.parent().children('.cchub-more-btn:last-child').append(
                    '<div class="cchub-icon cchub-' + type + '"></div>'
                );
                b.parent().parent().addClass('cchub-' + type);
            });
        });
    });
}