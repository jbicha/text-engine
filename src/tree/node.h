/* node.h
 *
 * Copyright 2022 Matthew Jakeman <mjakeman26@outlook.co.nz>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <glib-object.h>

G_BEGIN_DECLS

#define TEXT_TYPE_NODE (text_node_get_type())

G_DECLARE_DERIVABLE_TYPE (TextNode, text_node, TEXT, NODE, GObject)

struct _TextNodeClass
{
    GObjectClass parent_class;
};

// Implementors Only
TextNode *text_node_get_parent          (TextNode *self);
TextNode *text_node_get_next            (TextNode *self);
TextNode *text_node_get_previous        (TextNode *self);
TextNode *text_node_get_first_child     (TextNode *self);
TextNode *text_node_get_last_child      (TextNode *self);

void      text_node_insert_child        (TextNode *self, TextNode *child, int index);
void      text_node_prepend_child       (TextNode *self, TextNode *child);
void      text_node_append_child        (TextNode *self, TextNode *child);
void      text_node_insert_child_before (TextNode *self, TextNode *child, TextNode *compare);
void      text_node_insert_child_after  (TextNode *self, TextNode *child, TextNode *compare);

G_END_DECLS