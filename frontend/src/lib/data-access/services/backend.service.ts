import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { BoardI } from '../interfaces/boardI';
import { ItemI } from '../interfaces/itemI';
import { ListI } from '../interfaces/listI';

@Injectable({
  providedIn: 'root',
})
export class BackendService {
  readonly url: string = 'http://localhost:4200';

  constructor(private httpClient: HttpClient) {}

  loadBoard(): Observable<BoardI> {
    return this.httpClient.get<BoardI>(this.url + '/api/board');
  }
  createList(list: ListI): Observable<ListI> {
    let listPayload = {
      ...list,
    };
    return this.httpClient.post<ListI>(
      this.url + '/api/board/lists',
      listPayload
    );
  }

  createItem(listId: number, item: ItemI): Observable<ItemI> {
    let itemPayload = {
      ...item,
    };
    return this.httpClient.post<ItemI>(
      this.url + '/api/board/lists/' + listId + '/items',
      itemPayload
    );
  }
  updateList(list: ListI): Observable<ListI> {
    let listPayload = {
      ...list,
    };

    return this.httpClient.put<ListI>(
      this.url + '/api/board/lists/' + list.id,
      listPayload
    );
  }

  deleteItem(listId: number, itemId: number): Observable<void> {
    return this.httpClient.delete<void>(
      this.url + '/api/board/lists/' + listId + '/items/' + itemId
    );
  }

  updateItem(listId: number, item: ItemI): Observable<ItemI> {
    let itemPayload = {
      ...item,
    };

    return this.httpClient.put<ItemI>(
      this.url + '/api/board/lists/' + listId + '/items/' + item.id,
      itemPayload
    );
  }
}
